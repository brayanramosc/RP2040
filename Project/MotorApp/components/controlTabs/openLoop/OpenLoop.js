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

// constants
import { HEADER_SIGN, HEADER_BYTE } from '../constants';

const OpenLoop = () => {
    const [auxValue, setAuxValue] = useState(0);
    const [value, setValue] = useState(0);
    
    const chekLength = (val) => {
        val = val.toString(16);
        return val.length == 1 ? '0' + val : val;
    }

    const sendData = async() => {
        const val = parseInt(auxValue);
        const checksum = (HEADER_BYTE + val) & 0xFF;
        const block = HEADER_SIGN + chekLength(val) + chekLength(checksum);
        console.log("Trama: ", block);
        await BluetoothSerial.write(block);
    }

    const onChange = (val, _) => setAuxValue(val)

    const onSubmit = () => {
        if (auxValue !== '') {
            setValue(auxValue);
            sendData();
        }
    }

    return (
        <View style={panelStyles.container} >
            <Text style={panelStyles.title} >
                Control en lazo abierto
            </Text>
            <Image
                source={control_panel}
                style={panelStyles.img}
            />

            <View style={panelStyles.percSliderWrapper} >
                <View style = { panelStyles.inputWrapper } >
                    <ConstantInput 
                        constantName = { '%' } 
                        value = { auxValue } 
                        onChange = { onChange }
                    />
                    <TouchableOpacity 
                        onPress={onSubmit}
                        style={panelStyles.button} 
                    >
                        <Text style={panelStyles.textButton} >
                            Establecer valor
                        </Text>
                    </TouchableOpacity>
                </View>
                <View style={panelStyles.percWrapper} >
                    <Image
                        source={motor_icon}
                    />
                    <Text style={panelStyles.percText} >
                        {' Motor: ' + value.toString() + '%'}
                    </Text>
                </View>
                <CustomSlider min={0} max={100} step={5} value={value} onChange={setValue}/>
            </View>
        </View>
    )
}

export default OpenLoop;
