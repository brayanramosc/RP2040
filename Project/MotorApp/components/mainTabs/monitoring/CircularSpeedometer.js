import React from 'react';
import { Text } from 'react-native-svg';
import Speedometer, {
  Indicator,
  Progress,
  Arc
} from 'react-native-cool-speedometer';

const CircularSpeedometer = ({value}) => {
    const width = 140;
    const center = width / 2;

    return (
        <Speedometer
            value={value}
            max={100}
            angle={360}
            width={width}
            lineCap="round"
            accentColor="orange"
        >
            <Arc arcWidth={20} />
            <Progress arcWidth={20} />
            <Indicator>
                {(value, textProps) => (
                <Text
                    {...textProps}
                    fontSize={25}
                    fontWeight='bold'
                    fill="orange"
                    x={center - 7}
                    y={center}
                    textAnchor="middle"
                    alignmentBaseline="middle"
                >
                    {value}%
                </Text>
                )}
            </Indicator>
        </Speedometer>
    )
}

export default CircularSpeedometer;
