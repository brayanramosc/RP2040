import React from 'react';
import { Text, View, StyleSheet, Image, TouchableOpacity } from "react-native";
import embedded_systems from '../../assets/embedded-systems1.png';

const Home = ({ navigation }) => {
    return (
        <View style={styles.container} >
            <Image
                source={embedded_systems}
                style={styles.img}
            />
            <Text style={styles.title} >
                Sistema de Control y Monitoreo
            </Text>
            <Text style={styles.subtitle} >
                Sistemas Embebidos Avanzados - 2021-2
            </Text>
            {/*<TouchableOpacity 
                onPress={() => navigation.navigate('Bluetooth')}
                style={styles.button} 
            >
                <Text style={styles.textButton} >
                    Ingresar
                </Text>
            </TouchableOpacity>*/}
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        flex: 1, 
        justifyContent: 'center', 
        alignItems: 'center',
        backgroundColor: '#292929'
    },
    title: {
        textAlign: 'center',
        fontSize: 30,
        fontWeight: 'bold',
        color: 'white'
    },
    subtitle: {
        textAlign: 'center',
        fontSize: 20,
        color: 'white',
        marginBottom: 50
    },
    textButton: {
        textAlign: 'center',
        fontSize: 20,
        color: 'white'
    },
    img: {
        height: 200, 
        width: 200
    },
    button: {
        backgroundColor: 'deepskyblue',
        padding: 7,
        paddingTop: 2,
        marginTop: 10,
        borderRadius: 5
    }
})

export default Home;
