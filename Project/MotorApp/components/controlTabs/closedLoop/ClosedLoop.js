import React, { useState } from 'react';
import { View, Image, Text, TouchableOpacity } from 'react-native';
import BluetoothSerial from 'react-native-bluetooth-serial-next';

// Components
import CustomSlider from '../CustomSlider';
import ConstantInput from './ConstantInput';

// Images
import control_panel from '../../../assets/admin-panel.png';
import motor_icon from '../../../assets/motor.png';

// Styles
import { panelStyles } from './styles';

import { HEADER_SIGN, HEADER_BYTE, CONTROL_BYTE, CLOSED_LOOP_BYTE, P_VALUE_BYTE, I_VALUE_BYTE } from '../../constants';

const ClosedLoop = () => {
    const [value, setValue] = useState(0);
    const [pValue, setPValue] = useState(0);
    const [iValue, setIValue] = useState(0);

    const chekLength = (val) => {
        val = val.toString(16);
        return val.length == 1 ? '0' + val : val;
    }

    const sendData = async(val, id) => {
        const checksum = (HEADER_BYTE + (CONTROL_BYTE | id) + val) & 0xFF;
        const block = HEADER_SIGN + chekLength(CONTROL_BYTE | id) + chekLength(val) + chekLength(checksum);
        console.log("Trama: ", block);
        await BluetoothSerial.write(block);
    }

    const onValuesChange = (value, constantName) => {
        (constantName === 'P') ? setPValue(value) : setIValue(value);
    }

    const onSlideChange = (val, _) => {
        setValue(val);
        sendData(parseInt(val), CLOSED_LOOP_BYTE);
    }

    const onSubmit = () => {
        sendData(parseInt(pValue), P_VALUE_BYTE);
        sendData(parseInt(iValue), I_VALUE_BYTE);
    }

    return (
        <View style={panelStyles.container} >
            <Text style={panelStyles.title} >
                Control en lazo cerrado
            </Text>
            <Image
                source={control_panel}
                style={panelStyles.img}
            />

            <View style={panelStyles.percSliderWrapper} >
                <View style={panelStyles.percWrapper} >
                    <Image
                        source={motor_icon}
                    />
                    <Text style={panelStyles.percText} >
                        {' Motor: ' + value.toString() + ' RPM'}
                    </Text>
                </View>
                <CustomSlider min={0} max={200} step={5} value={value} onChange={onSlideChange}/>
                <ConstantInput 
                    constantName = { 'P' } 
                    value = { pValue } 
                    onChange = { onValuesChange }
                />
                <ConstantInput 
                    constantName = { 'I' } 
                    value = { iValue } 
                    onChange = { onValuesChange }
                />
                <TouchableOpacity 
                    onPress={onSubmit}
                    style={panelStyles.button} 
                >
                    <Text style={panelStyles.textButton} >
                        Establecer valores
                    </Text>
                </TouchableOpacity>
            </View>
        </View>
    )
}

export default ClosedLoop;
