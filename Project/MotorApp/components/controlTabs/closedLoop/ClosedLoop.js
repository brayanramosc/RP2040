import React, { useState } from 'react';
import { View, Image, Text, TouchableOpacity } from 'react-native';

// Components
import CustomSlider from '../CustomSlider';
import ConstantInput from './ConstantInput';

// Images
import control_panel from '../../../assets/admin-panel.png';
import motor_icon from '../../../assets/motor.png';

// Styles
import { panelStyles } from './styles';

const ClosedLoop = () => {
    const [value, setValue] = useState(0);
    const [pValue, setPValue] = useState(0);
    const [iValue, setIValue] = useState(0);

    const onChange = (value, constantName) => {
        (constantName === 'P') ? setPValue(value) : setIValue(value);
    }

    const onSubmit = () => {
        if (value !== '') {
            console.log("P: ", pValue);
            console.log("I: ", iValue);
        }
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
                        {' Motor: ' + value.toString() + '%'}
                    </Text>
                </View>
                <CustomSlider min={0} max={100} step={5} value={value} onChange={setValue}/>
                <ConstantInput 
                    constantName = { 'P' } 
                    value = { pValue } 
                    onChange = { onChange }
                />
                <ConstantInput 
                    constantName = { 'I' } 
                    value = { iValue } 
                    onChange = { onChange }
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
