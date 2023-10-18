import React from "react";
import { NavigationContainer } from '@react-navigation/native';

// components
import DrawerNavigation from "./components/navigation/DrawerNavigation";

const App = () => {
	return (
		<NavigationContainer>
			<DrawerNavigation />
		</NavigationContainer>
	);
}

export default App;
