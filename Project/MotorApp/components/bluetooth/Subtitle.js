import React from 'react';
import { Text, View, StyleSheet } from "react-native";

const Subtitle = ({ title }) => {
    return (
        <View style={styles.container} >
            <Text style={styles.title} >{ title }</Text>
            <View style={styles.line} />
        </View>
    );
}

const styles = StyleSheet.create({
    container: {
        flexDirection: 'row',
        marginVertical: 15,
        alignItems: 'center'
    },
    title: {
        fontSize: 18,
        fontWeight: 'bold',
        color: 'gray'
    },
    line: {
        borderBottomWidth: 1,
        marginLeft: 5,
        flex: 1,
        marginTop: 3,
        borderColor: '#ECEFF1'
    }
})

export default Subtitle;
