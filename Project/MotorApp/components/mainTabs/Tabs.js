import React, { useState } from 'react';
import { useWindowDimensions } from "react-native";
import { TabView, SceneMap } from 'react-native-tab-view';

import ControlPanel from './control/ControlPanel';
import MonitoringPanel from './monitoring/MonitoringPanel';

const FirstRoute = () => (
    <ControlPanel />
);

const SecondRoute = () => (
    <MonitoringPanel />
);

const renderScene = SceneMap({
    first: FirstRoute,
    second: SecondRoute,
});

const Tabs = () => {
    const [index, setIndex] = useState(0);
    const layout = useWindowDimensions();

    const [routes] = React.useState([
        { key: 'first', title: 'Control' },
        { key: 'second', title: 'Monitoreo' },
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
