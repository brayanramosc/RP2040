import React from 'react';
import { Dimensions, View, Text, StyleSheet } from 'react-native';
import { BarChart } from "react-native-chart-kit";

const screenWidth = Dimensions.get("window").width;

const chartConfig = {
    //backgroundGradientFrom: "#1E2923",
    //backgroundGradientFromOpacity: 0,
    //backgroundGradientTo: "#08130D",
    //backgroundGradientToOpacity: 0.5,
    backgroundGradientFrom: "#FFFFFF",
    backgroundGradientFromOpacity: 0,
    backgroundGradientTo: "#FFFFFF",
    backgroundGradientToOpacity: 0.5,

    fillShadowGradientOpacity: 0.5,
    //color: (opacity = 1) => `rgba(0, 255, 0, ${opacity})`,
    color: (_) => `#023047`,
    labelColor: (_) => `#333333`,
    strokeWidth: 2,
    
    barPercentage: 1,
    useShadowColorFromDataset: false,
    decimalPlaces: 0,
};

const CustomBarChart = ({ values }) => {
    let data = {
        labels: ["Set point", "Valor actual"],
        datasets: [
            {
                data: values || [100, 90]
            }
        ],
        legend: ["Sales Chart"] // optional
    };

    return (
        <View style = { styles.container } >
            <View style={styles.titleContainer}>
                <Text style={styles.text} >Visualización</Text>
            </View>
            <BarChart
                style = {{
                    marginVertical: 10,
                    borderRadius: 16,
                }}
                data = { data }
                width = { parseInt(screenWidth / 1.1) - 30}
                height = { 300 }
                fromZero = { true }
                //yAxisInterval = {10}
                yLabelsOffset = { 5 }
                yAxisSuffix = " RPM"
                chartConfig = { chartConfig }
                verticalLabelRotation = { 0 }
                showValuesOnTopOfBars = {true}
            />
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        marginBottom: 20,
    },
    titleContainer: {
        alignItems: 'center',
    },
    text: {
        fontSize: 20,
        fontWeight: 'bold',
        color: 'black'
    }
});

export default CustomBarChart;
