import React from 'react';
import { View, Text, StyleSheet, TextInput } from 'react-native';

const ConstantInput = ({ constantName, value, onChange }) => {
    return (
        <View style = { styles.container } >
            <Text style = { styles.text } >
                {constantName + ': '}
            </Text>
            <TextInput 
                value = { String(value) }
                style = { styles.input }
                placeholder = { 'Constant ' + constantName }
                keyboardType = 'numeric'
                onChangeText = { (value) => {onChange(value, constantName)} }
            />
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        flexDirection: 'row',
        alignItems: 'center',
    },
    text: {
        color: 'black',
        fontSize: 15,
        fontWeight: 'bold'
    },
    input: {
        height: 40,
        width: 100,
        margin: 10,
        borderWidth: 1,
        padding: 10
    }
})

export default ConstantInput;
