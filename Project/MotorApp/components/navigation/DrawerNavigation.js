import React from 'react';
import { createDrawerNavigator, DrawerContentScrollView } from '@react-navigation/drawer';
import { Text, StyleSheet } from 'react-native';

// components
import Home from '../home/Home';
import Bluetooth from '../bluetooth/Bluetooth';
import MotorInformation from '../motorInformation/MotorInformation';
import MenuItem from './MenuItem';

// Images
import home_icon from '../../assets/home.png';
import bluetooth_icon from '../../assets/bluetooth_color.png';
import info_icon from '../../assets/information.png';

const Drawer = createDrawerNavigator();

const MenuItems = ({ navigation }) => {
	return (
		<DrawerContentScrollView
			style={styles.container}
		>
			<Text style={styles.title}> Menú </Text>
			<MenuItem
				text = 'Inicio'
				onPress = { () => navigation.navigate('Inicio') }
				imgPath = {home_icon}
			/>
			<MenuItem
				text = 'Sincronización'
				onPress = { () => navigation.navigate('Sincronización') }
				imgPath = {bluetooth_icon}
			/>
			<MenuItem
				text = 'Información del motor'
				onPress = { () => navigation.navigate('Información del motor') }
				imgPath = {info_icon}
			/>
		</DrawerContentScrollView>
	)
}

const DrawerNavigation = () => {
	return (
		<Drawer.Navigator 
			initialRouteName="Home"
			drawerContent={ (props) => <MenuItems {...props} /> }
		>
			<Drawer.Screen name="Inicio" component={Home} />
			<Drawer.Screen name="Sincronización" component={Bluetooth} />
			<Drawer.Screen name="Información del motor" component={MotorInformation} />
		</Drawer.Navigator>
	)
}

const styles = StyleSheet.create({
    container: {
        padding: 15
    },
    title: {
        fontSize: 20,
		color: 'black',
        fontWeight: 'bold',
		marginBottom: 20
    }
})

export default DrawerNavigation;
