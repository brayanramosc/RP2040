import { StyleSheet } from "react-native";

export const panelStyles = StyleSheet.create({
    container: {
        flex: 1, 
        justifyContent: 'flex-start', 
        backgroundColor: 'white',
        alignItems: 'center',
        padding: 10
    },
    title: {
        textAlign: 'center',
        fontSize: 30,
        fontWeight: 'bold',
        color: 'black',
        paddingVertical: 20
    },
    img: {
        alignSelf: 'center',
        marginBottom: 40,
        height: 100, 
        width: 100
    },
    chartWrapper: {
        //flex: 1, 
        flexDirection: 'row',
        //justifyContent: 'flex-start', 
        backgroundColor: 'white',
        alignItems: 'center',
        padding: 10
    },
})
