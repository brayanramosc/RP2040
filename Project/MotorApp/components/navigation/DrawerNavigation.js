import React from 'react';
import { createDrawerNavigator } from '@react-navigation/drawer';

// components
import Home from '../home/Home';
import Bluetooth from '../bluetooth/Bluetooth';
import MotorInformation from '../motorInformation/MotorInformation';

const Drawer = createDrawerNavigator();

const DrawerNavigation = () => {
	return (
		<Drawer.Navigator initialRouteName="Home">
			<Drawer.Screen name="Inicio" component={Home} />
			<Drawer.Screen name="Sincronización" component={Bluetooth} />
			<Drawer.Screen name="Información del motor" component={MotorInformation} />
		</Drawer.Navigator>
	)
}

export default DrawerNavigation;
