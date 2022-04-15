import React from 'react';
import Slider from '@react-native-community/slider';
import { useWindowDimensions } from "react-native";

const CustomSlider = ({ min, max, step, onChange }) => {
    const layout = useWindowDimensions();

    return (
        <Slider
            style={{width: parseInt(layout.width*0.75), height: 40}}
            minimumValue={min}
            maximumValue={max}
            step={step}
            minimumTrackTintColor="tomato"
            maximumTrackTintColor="#000000"
            thumbTintColor='tomato'
            onValueChange={onChange}
            onSlidingComplete={onChange}
        />
    )
}

export default CustomSlider;
