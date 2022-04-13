import React from 'react';
//import { SafeAreaView, StyleSheet, TextInput } from 'react-native';
import RNSpeedometer from 'react-native-speedometer';

const labels = [
    {
        name: 'Muy frío',
        labelColor: '#0047AB',
        activeBarColor: '#0047AB',
    },
    {
        name: 'Frío',
        labelColor: '#0096FF',
        activeBarColor: '#0096FF',
    },
    {
        name: 'Normal  ',
        labelColor: '#F2CF1F',
        activeBarColor: '#F2CF1F',
    },
    {
        name: 'Normal ',
        labelColor: '#F2CF1F',
        activeBarColor: '#F2CF1F',
    },
    {
        name: 'Normal',
        labelColor: '#F2CF1F',
        activeBarColor: '#F2CF1F',
    },
    {
        name: 'Caliente ',
        labelColor: '#FF5400',
        activeBarColor: '#FF5400',
    },
    {
        name: 'Caliente',
        labelColor: '#FF5400',
        activeBarColor: '#FF5400',
    },
    {
        name: 'Muy caliente',
        labelColor: '#FF2900',
        activeBarColor: '#FF2900',
    },
]

const Thermotast = ({value}) => {

    return (
        <RNSpeedometer 
            value={value} 
            labels={labels}
            size={150}
            minValue={0}
            maxValue={150}
        />
    )
}

export default Thermotast;
