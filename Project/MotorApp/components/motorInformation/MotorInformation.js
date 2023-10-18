import React from 'react';
import { View, Text, StyleSheet, Image } from 'react-native';

import Feature from './Feature';

import feature_list from '../../assets/feature_list.png'

const MotorInformation = () => {
    return (
        <View style={styles.container} >
            <Text style={styles.title} >
                Características
            </Text>
            <Image
                source={feature_list}
                style={styles.img}
            />
            <Feature name={'Voltaje máxima'} value={'6 V'} />
            <Feature name={'Velocidad máxima'} value={'200 RPM'} />
            <Feature name={'Velocidad mínima'} value={'10 RPM'} />
            <Feature name={'Rango de control'} value={'50 RPM - 160 RPM'} />
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        flex: 1, 
        padding: 20,
        backgroundColor: '#FFFFFF'
    },
    title: {
        textAlign: 'center',
        fontSize: 30,
        fontWeight: 'bold',
        marginBottom: 10,
        color: 'black'
    },
    img: {
        marginBottom: 50,
        alignSelf: 'center'
    }
})

export default MotorInformation;
