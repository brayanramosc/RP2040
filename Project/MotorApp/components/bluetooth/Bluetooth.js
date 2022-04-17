import React, { useState } from 'react';
import { Text, View, StyleSheet, FlatList, Alert } from "react-native";
import BluetoothSerial from 'react-native-bluetooth-serial-next';

// Components
import Subtitle from './Subtitle';
import Device from './Device';
import Toggle from './Toggle';

const Bluetooth = ({ navigation }) => {
    const [deviceList, setDeviceList] = useState([]);
    const [enable, setEnable] = useState(false);

    const onPress = async(id) => {
        console.log(id);
        try {
            await BluetoothSerial.connect(id);
            //navigation.navigate('Monitoreo y control');
        } catch (error) {
            console.log(error);
            Alert.alert(
                "Error de conexión",
                "No se pudo establecer conexión con el dispositivo.",
                [
                    { text: "OK", onPress: () => console.log("OK") }
                ]
            );
        }
    }
    
    const renderEmpty = () => <Text>{'No hay dispositivos'}</Text>;
    const renderItem = ({item}) => {
        return <Device {...item} onPress={onPress} />
    }

    const enableBluetooth = async() => {
        try {
            await BluetoothSerial.requestEnable();
            const devices = await BluetoothSerial.list();
            await BluetoothSerial.stopScanning();
            setDeviceList(devices);
            setEnable(true);
        } catch (error) {
            console.log(error);
        }
    }

    const disableBluetooth = async() => {
        try {
            await BluetoothSerial.disable();
            await BluetoothSerial.stopScanning();
            setEnable(false);
            setDeviceList([]);
        } catch (error) {
            console.log(error);
        }
    }

    const toggleBluetooth = (value) => {
        if (value) {
            return enableBluetooth();
        }
        disableBluetooth();
    }

    return (
        <View style={styles.container} >
            <Toggle isEnable={enable} onValueChange={toggleBluetooth} />
            <Subtitle title={'Lista de Dispositivos'} />
            <FlatList  
                data={deviceList}
                ListEmptyComponent={renderEmpty}
                renderItem={renderItem}
            />
        </View>
    );
}

const styles = StyleSheet.create({
    container: {
        flex: 1, 
        justifyContent: 'flex-start', 
        padding: 10,
        backgroundColor: 'white'
    }
})

export default Bluetooth;
