import { StyleSheet } from 'react-native';

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
    percSliderWrapper: {
        flexDirection: 'column',
        alignItems: 'center',
        paddingBottom: 30
    },
    percWrapper: {
        flexDirection: 'row',
        alignItems: 'center'
    },
    percText: {
        textAlign: 'center',
        fontSize: 25,
        fontWeight: 'bold',
        color: 'black'
    },
    img: {
        alignSelf: 'center',
        marginBottom: 40,
        height: 100, 
        width: 100
    },
    textButton: {
        textAlign: 'center',
        fontSize: 18,
        color: 'white'
    },
    button: {
        backgroundColor: 'deepskyblue',
        padding: 8,
        borderRadius: 5
    }
})