import React from 'react';
import { TouchableOpacity, Text, StyleSheet, Image } from 'react-native';

const MenuItem = ({ text, onPress, imgPath }) => {
    return (
        <TouchableOpacity
            style = { styles.buttonContainer }
            onPress = { onPress }
        >
            <Image 
                source = { imgPath }
                style = { styles.image }
            />
            <Text style = { styles.text } > {text} </Text>
        </TouchableOpacity>
    )
}

const styles = StyleSheet.create({
    buttonContainer: {
        alignItems: 'center',
        backgroundColor: '#D8F8F2',
        flexDirection: 'row',
        borderRadius: 10,
        marginBottom: 15,
        padding: 15
    },
    text: {
        color: 'black',
        fontSize: 15,
        fontWeight: 'bold',
        marginStart: 10
    },
    image: {
        borderRadius: 16,
        height: 32,
        width: 32
    }
})

export default MenuItem;
