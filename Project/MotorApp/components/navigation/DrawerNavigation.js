import React from 'react';
import { createDrawerNavigator, DrawerContentScrollView } from '@react-navigation/drawer';
import { Text, StyleSheet } from 'react-native';

// components
import Home from '../home/Home';
import Bluetooth from '../bluetooth/Bluetooth';
import MotorInformation from '../motorInformation/MotorInformation';
import MonitoringPanel from '../monitoring/MonitoringPanel';
import Tabs from '../controlTabs/Tabs';
import MenuItem from './MenuItem';

// Images
import home_icon from '../../assets/home.png';
import bluetooth_icon from '../../assets/bluetooth_color.png';
import info_icon from '../../assets/information.png';
import monitoring_icon from '../../assets/analysis.png';
import control_icon from '../../assets/supervision.png'

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
			<MenuItem
				text = 'Panel de monitoreo'
				onPress = { () => navigation.navigate('Panel de monitoreo') }
				imgPath = {monitoring_icon}
			/>
			<MenuItem
				text = 'Panel de control'
				onPress = { () => navigation.navigate('Panel de control') }
				imgPath = {control_icon}
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
			<Drawer.Screen name="Panel de monitoreo" component={MonitoringPanel} />
			<Drawer.Screen name="Panel de control" component={Tabs} />
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
