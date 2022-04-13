import React from 'react';
import Slider from '@react-native-community/slider';
import { View, useWindowDimensions } from "react-native";

const CustomSlider = (props) => {
    const layout = useWindowDimensions();

    return (
        <Slider
            style={{width: parseInt(layout.width*0.75), height: 40}}
            minimumValue={props.min}
            maximumValue={props.max}
            step={props.step}
            minimumTrackTintColor="tomato"
            maximumTrackTintColor="#000000"
            thumbTintColor='tomato'
            onValueChange={props.onChange}
            onSlidingComplete={props.onChange}
        />
    )
}

export default CustomSlider;
