import React from 'react';
import { View, Text, StyleSheet } from 'react-native';

const ErrorDisplay = ({ errorValue }) => {
    return (
        <View style = { styles.container } >
            <Text style = { styles.title } >
                Error
            </Text>
            <Text style = { styles.value } >
                { String(errorValue) + '%'}
            </Text>
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        padding: 15,
        alignItems: 'center'
    },
    title: {
        fontSize: 20,
		color: 'black',
        fontWeight: 'bold',
		marginBottom: 10
    },
    value: {
        fontSize: 18,
        width: 70,
        textAlign: 'center',
        borderWidth: 2,
        padding: 4,
        color: 'red',
        fontWeight: 'bold'
    }
})

export default ErrorDisplay;
