import React, { useEffect, useState } from 'react';
import { Text, View, Image } from "react-native";
import BluetoothSerial from 'react-native-bluetooth-serial-next';

// Components
import Thermotast from './Thermotast';
import CircularSpeedometer from './CircularSpeedometer';

// Styles
import { panelStyles } from './styles';

// Images
import monitoring_panel from '../../../assets/monitoring.png';

// constants
import { HEADER_SIGN, HEADER_BYTE, MONITOR_BYTE, LIGHT_BYTE, TEMPERATURE_BYTE } from '../constants';
import { ST_START, ST_GET_MODE, ST_GET_VALUE, ST_GET_CS } from '../constants';

let state = ST_START;
let tempValue = 0;
let tempCS = 0;

const MonitoringPanel = () => {
    const [temperature, setTemperature] = useState(0);
    const [lightPerc, setLightPerc] = useState(0);

    const chekLength = (val) => {
        val = val.toString(16);
        return val.length == 1 ? '0' + val : val;
    }

    const FSM = (data, actByte) => {
        if (data.length >= 4) {
            for (let index = 0; index < data.length; index++) {
                const byte = data[index];

                switch (state) {
                    case ST_START:
                        console.log("State and ch: ", state, byte, byte.charCodeAt());
                        state = (byte == '$') ? ST_GET_MODE : ST_START;
                        break;
        
                    case ST_GET_MODE:
                        console.log( "State and ch: ", state, byte, byte.charCodeAt() );
                        state = (byte.charCodeAt() == (MONITOR_BYTE | actByte)) ? ST_GET_VALUE : ST_START;
                        break;
        
                    case ST_GET_VALUE:
                        console.log("State and ch: ", state, byte, byte.charCodeAt());
                        tempValue = byte.charCodeAt();
                        state = ST_GET_CS;
                        break;
        
                    case ST_GET_CS:
                        console.log("State and ch: ", state, byte, byte.charCodeAt());
                        tempCS = (HEADER_BYTE + (MONITOR_BYTE | actByte) + tempValue) & 0xFF;
                        
                        if (tempCS == byte.charCodeAt()) {
                            console.log("Value: ", tempValue);
                            if (actByte == LIGHT_BYTE) setLightPerc(tempValue);
                            else setTemperature(tempValue);
                        }
                        state = ST_START;
                        break;
                
                    default:
                        break;
                }
            }
        }
    }

    const readData = async(actByte) => {
        const checksum = (HEADER_BYTE + (MONITOR_BYTE | actByte)) & 0xFF;
        const block = HEADER_SIGN + chekLength(MONITOR_BYTE | actByte) + chekLength(0x00) + chekLength(checksum);
        await BluetoothSerial.write(block);
            
        setTimeout(async() => {
            //var date1 = new Date();
            const data = await BluetoothSerial.readFromDevice();
            
            console.log("Data: ", data);
            FSM(data, actByte);
        }, 100);
    }
    

    useEffect(() => {
        const lightInterval = setInterval(async() => {
            readData(LIGHT_BYTE);
        }, 1000);

        const temperatureInterval = setInterval(async() => {
            readData(TEMPERATURE_BYTE);
        }, 1300);

        return () => {
            clearInterval(lightInterval);
            clearInterval(temperatureInterval);
        };
      }, [])
      
    return (
        <View style={panelStyles.container} >
            <Text style={panelStyles.title} >
                Panel de monitoreo
            </Text>
            <Image
                source={monitoring_panel}
                style={panelStyles.img}
            />

            <View style={panelStyles.chartWrapper} >
                <View style={{alignItems: 'center', paddingRight: 20}}>
                    <Text style={{marginBottom: 5}} >
                        Porcentaje de luz
                    </Text>
                    <CircularSpeedometer value={lightPerc} />
                </View>
                
                <View style={{alignItems: 'center', height: 160}}>
                    <Text style={{marginBottom: 20}} >
                        Temperatura [°C]
                    </Text>
                    <Thermotast value={temperature} />
                </View>
            </View>
        </View>
    )
}

export default MonitoringPanel;
