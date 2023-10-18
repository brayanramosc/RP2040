import React from 'react';
import { View, Text, StyleSheet } from 'react-native';

const Feature = ({ name, value }) => {
    return (
        <View style={styles.container} >
            <Text style={styles.name}>
                {name + ': '}
            </Text>
            <Text style={styles.value}>
                {value}
            </Text>
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        //flex: 1,
        flexDirection: 'row',
        //justifyContent: 'flex-start',
        paddingBottom: 15, 
        alignItems: 'flex-end',
        backgroundColor: '#FFFFFF'
    },
    name: {
        //textAlign: 'center',
        fontSize: 20,
        fontWeight: 'bold',
        //marginBottom: 10,
        color: 'black'
    },
    value: {
        fontSize: 18,
        color: 'black',
        //marginBottom: 10
    }
})

export default Feature;
