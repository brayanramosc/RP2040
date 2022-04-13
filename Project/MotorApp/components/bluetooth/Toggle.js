import React from 'react';
import { Text, View, StyleSheet, Switch } from "react-native";

const Toggle = ({isEnable, onValueChange}) => {
    return (
        <View style={styles.container} >
            <Text style={styles.text} >{isEnable ? 'Activado':'Desactivado'}</Text>
            <Switch 
                style={styles.switch}
                value={isEnable}
                onValueChange={onValueChange}
            />
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        paddingVertical: 15,
        justifyContent: 'space-between',
        flexDirection: 'row'
    },
    text: {
        fontSize: 18,
        fontWeight: 'bold',
        color: 'black'
    },
    switch: {
        width: 50
    }
})

export default Toggle;
