import React from "react";
import { NavigationContainer } from '@react-navigation/native';
import { createDrawerNavigator } from '@react-navigation/drawer';

// components
import DrawerNavigation from "./components/navigation/DrawerNavigation";

const Drawer = createDrawerNavigator();

const App = () => {
	return (
		<NavigationContainer>
			<DrawerNavigation />
		</NavigationContainer>
	);
}

export default App;
