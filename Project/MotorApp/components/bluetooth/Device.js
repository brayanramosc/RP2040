import React from 'react';
import { Text, View, StyleSheet, Image, TouchableOpacity } from "react-native";

import bluetoothImg from '../../assets/bluetooth.png';

const Device = (props) => {
    return (
        <>
            <TouchableOpacity style={styles.wrapper} onPress={() => props.onPress(props.id)} >
                <View style={styles.wrapperLeft} >
                    <Image style={styles.iconLeft} source={bluetoothImg} />
                </View>
                <View style={styles.wrapperName} >
                    <Text style={styles.nameText} >
                        {props.name}
                    </Text>
                </View>
            </TouchableOpacity>
            <View style={styles.separator} />
        </>
    )
}

const styles = StyleSheet.create({
    wrapper: {
        flexDirection: 'row',
        padding: 10,
        alignItems: 'center',
        justifyContent: 'space-between'
    },
    wrapperLeft: {
        width: 40,
        height: 40,
        borderRadius: 20,
        borderColor: 'gray',
        borderWidth: 1,
        flexDirection: 'column',
        justifyContent: 'center',
        alignItems: 'center'
    },
    wrapperName: {
        flex: 1,
        justifyContent: 'flex-start',
        marginLeft: 15
    },
    nameText: {
        fontSize: 20
    },
    separator: {
        flex: 1,
        borderTopWidth: 1,
        marginLeft: 60,
        marginRight: 25,
        borderColor: '#ECEFF1'
    }
})

export default Device;
