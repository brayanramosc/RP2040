import React, { useState } from 'react';
import { View, StyleSheet, Dimensions } from 'react-native';

// Components
import CustomBarChart from './CustomBarChart';
import ErrorDisplay from './ErrorDisplay';

const screenHeight = Dimensions.get("window").height;

const MonitoringPanel = () => {
    const [setPoint, setSetPoint] = useState(100);
    const [currentValue, setCurrentValue] = useState(80);

    return (
        <View style = { styles.container } >
            <CustomBarChart values = { [setPoint, currentValue] } />
            <ErrorDisplay errorValue = { 100 - ((currentValue / setPoint) * 100) } />
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        padding: 15,
        backgroundColor: 'white',
        height: screenHeight
    }
})

export default MonitoringPanel;
