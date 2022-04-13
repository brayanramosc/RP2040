import React, { useState } from 'react';
import { Text, View, Image } from "react-native";
import BluetoothSerial from 'react-native-bluetooth-serial-next';

// Components
import CustomSlider from './CustomSlider';

// Images
import control_panel from '../../../assets/admin-panel.png';
import motor_icon from '../../../assets/motor.png';
import led_icon from '../../../assets/led.png';

// Styles
import { panelStyles } from './styles';

// constants
import { HEADER_SIGN, HEADER_BYTE, CONTROL_BYTE, LED_BYTE, MOTOR_BYTE } from '../constants';

let value = 0x00;

const ControlPanel = () => {
    const [lightValue, setLightValue] = useState(0);
    const [tempValue, setTempValue] = useState(0);

    const chekLength = (val) => {
        val = val.toString(16);
        return val.length == 1 ? '0' + val : val;
    }

    const sendData = async(actByte) => {
        const checksum = (HEADER_BYTE + (CONTROL_BYTE | actByte) + value) & 0xFF;
        //const block = String.fromCharCode(HEADER_BYTE, (CONTROL_BYTE | actByte), value, checksum);
        const block = HEADER_SIGN + chekLength(CONTROL_BYTE | actByte) + chekLength(value) + chekLength(checksum);
        console.log("Trama: ", block);
        await BluetoothSerial.write(block);

        /*const data = await BluetoothSerial.readFromDevice().then((resp) => {
            console.log(resp);
        })*/
        /*for (let index = 0; index < data.length; index++) {
            const element = data[index];
            console.log("Elemento: ", element.charCodeAt().toString(16));
        }
        console.log("Data in control panel: ", data);*/
    }

    const onLightSliderChange = (val) => {
        value = val;
        setLightValue(value);
        sendData(LED_BYTE);
    }

    const onTempSliderChange = (val) => {
        value = val;
        setTempValue(value);
        sendData(MOTOR_BYTE);
    }

    return (
        <View style={panelStyles.container} >
            <Text style={panelStyles.title} >
                Panel de control
            </Text>
            <Image
                source={control_panel}
                style={panelStyles.img}
            />

            <View style={panelStyles.percSliderWrapper} >
                <View style={panelStyles.percWrapper} >
                    <Image
                        source={led_icon}
                    />
                    <Text style={panelStyles.percText} >
                        {' LED: ' + lightValue.toString() + '%'}
                    </Text>
                </View>
                <CustomSlider min={0} max={100} step={5} onChange={onLightSliderChange}/>
            </View>

            <View style={panelStyles.percSliderWrapper} >
                <View style={panelStyles.percWrapper} >
                    <Image
                        source={motor_icon}
                    />
                    <Text style={panelStyles.percText} >
                        {' Motor: ' + tempValue.toString() + '%'}
                    </Text>
                </View>
                <CustomSlider min={0} max={100} step={5} onChange={onTempSliderChange}/>
            </View>
        </View>
    )
}

export default ControlPanel;
