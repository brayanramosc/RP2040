import React, { useState, useEffect } from 'react';
import { View, StyleSheet, Dimensions } from 'react-native';
import BluetoothSerial from 'react-native-bluetooth-serial-next';

// Components
import CustomBarChart from './CustomBarChart';
import ErrorDisplay from './ErrorDisplay';

import { CURRENT_VALUE_BYTE, ERROR_BYTE } from '../constants';
import { ST_START, ST_GET_MODE, ST_GET_VALUE, ST_GET_CS } from '../constants';

const screenHeight = Dimensions.get("window").height;
let state = ST_START;
let tempValue = 0;
let tempCS = 0;

const MonitoringPanel = () => {
    const [setPoint, setSetPoint] = useState(100);
    const [currentValue, setCurrentValue] = useState(80);
    const [error, setError] = useState(0);

    const FSM = (data) => {
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
                        state = (byte.charCodeAt() == (MONITOR_BYTE | CURRENT_VALUE_BYTE)) ? ST_GET_VALUE : ST_START;
                        if (state == ST_START) {
                            state = (byte.charCodeAt() == (MONITOR_BYTE | ERROR_BYTE)) ? ST_GET_VALUE : ST_START;
                        }

                        break;
        
                    case ST_GET_VALUE:
                        console.log("State and ch: ", state, byte, byte.charCodeAt());
                        tempValue = byte.charCodeAt();
                        state = ST_GET_CS;
                        break;
        
                    case ST_GET_CS:
                        console.log("State and ch: ", state, byte, byte.charCodeAt());
                        if (data[1].charCodeAt() == (MONITOR_BYTE | CURRENT_VALUE_BYTE)) {
                            tempCS = (HEADER_BYTE + (MONITOR_BYTE | CURRENT_VALUE_BYTE) + tempValue) & 0xFF;
                            setCurrentValue(tempCS == byte.charCodeAt() ? tempValue : currentValue);
                        } else {
                            tempCS = (HEADER_BYTE + (MONITOR_BYTE | ERROR_BYTE) + tempValue) & 0xFF;
                            setError(tempCS == byte.charCodeAt() ? tempValue : error);
                        }
                        state = ST_START;
                        break;
                
                    default:
                        break;
                }
            }
        }
    }

    const readData = async() => {
        const data = await BluetoothSerial.readFromDevice();
        console.log("Data: ", data);
        FSM(data);
    }
    
    useEffect(() => {
        //const lightInterval = setInterval(async() => {
            readData();
            console.log("Hola!");
        //}, 1000);

        /*return () => {
            clearInterval(lightInterval);
            clearInterval(temperatureInterval);
        };*/
    }/*, []*/)

    return (
        <View style = { styles.container } >
            <CustomBarChart values = { [setPoint, currentValue] } />
            <ErrorDisplay errorValue = { 100 - ((currentValue / setPoint) * 100) } />
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        padding: 15,
        backgroundColor: 'white',
        height: screenHeight
    }
})

export default MonitoringPanel;
