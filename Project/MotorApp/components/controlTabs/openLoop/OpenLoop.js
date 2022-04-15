import React, { useState } from 'react';
import { View, Image, Text, StyleSheet } from 'react-native';

// Components
import CustomSlider from '../CustomSlider';

// Images
import control_panel from '../../../assets/admin-panel.png';
import motor_icon from '../../../assets/motor.png';

const OpenLoop = () => {
    const [value, setValue] = useState(0);

    return (
        <View style={styles.container} >
            <Text style={styles.title} >
                Control en lazo abierto
            </Text>
            <Image
                source={control_panel}
                style={styles.img}
            />

            <View style={styles.percSliderWrapper} >
                <View style={styles.percWrapper} >
                    <Image
                        source={motor_icon}
                    />
                    <Text style={styles.percText} >
                        {' Motor: ' + value.toString() + '%'}
                    </Text>
                </View>
                <CustomSlider min={0} max={100} step={5} onChange={setValue}/>
            </View>
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        flex: 1, 
        justifyContent: 'flex-start', 
        backgroundColor: 'white',
        alignItems: 'center',
        padding: 10
    },
    title: {
        textAlign: 'center',
        fontSize: 30,
        fontWeight: 'bold',
        color: 'black',
        paddingVertical: 20
    },
    percSliderWrapper: {
        flexDirection: 'column',
        alignItems: 'center',
        paddingBottom: 30
    },
    percWrapper: {
        flexDirection: 'row',
        alignItems: 'center'
    },
    percText: {
        textAlign: 'center',
        fontSize: 25,
        fontWeight: 'bold',
        color: 'black'
    },
    img: {
        alignSelf: 'center',
        marginBottom: 60,
        height: 100, 
        width: 100
    }
})

export default OpenLoop;
