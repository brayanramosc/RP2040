import React, { useState } from 'react';
import { useWindowDimensions } from "react-native";
import { TabView, SceneMap } from 'react-native-tab-view';

// Components
import OpenLoop from './openLoop/OpenLoop';
import ClosedLoop from './closedLoop/ClosedLoop';

const FirstRoute = () => (
    <OpenLoop />
);

const SecondRoute = () => (
    <ClosedLoop />
);

const renderScene = SceneMap({
    first: FirstRoute,
    second: SecondRoute,
});

const Tabs = () => {
    const [index, setIndex] = useState(0);
    const layout = useWindowDimensions();

    const [routes] = React.useState([
        { key: 'first', title: 'Lazo abierto' },
        { key: 'second', title: 'Lazo cerrado' },
    ]);

    return (
        <TabView
            navigationState={{ index, routes }}
            renderScene={renderScene}
            onIndexChange={setIndex}
            initialLayout={{ width: layout.width }}
        />
    )
}

export default Tabs;
