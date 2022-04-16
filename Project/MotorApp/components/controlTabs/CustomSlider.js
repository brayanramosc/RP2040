import React from 'react';
import Slider from '@react-native-community/slider';
import { useWindowDimensions } from "react-native";

const CustomSlider = ({ min, max, step, value, onChange }) => {
    const layout = useWindowDimensions();

    return (
        <Slider
            style={{
                width: parseInt(layout.width*0.75), 
                height: 30,
                marginBottom: 40
            }}
            minimumValue={min}
            maximumValue={max}
            step={step}
            minimumTrackTintColor="tomato"
            maximumTrackTintColor="#000000"
            thumbTintColor='tomato'
            value={parseInt(value) || 0}
            onValueChange={onChange}
            onSlidingComplete={onChange}
        />
    )
}

export default CustomSlider;
