import React, { useEffect, useRef } from 'react';
import Chart from 'chart.js/auto';

const TempChart = ({ data }) => {
    useEffect(() => {
        const chartCanvas = document.getElementById('temp-chart');
        const chartInstance = new Chart(chartCanvas, {
            type: 'line',
            data: {
                labels: data.map((d) => d.time),
                datasets: [
                    {
                        label: 'Temperature in °C',
                        data: data.map((d) => d.temperature),
                        fill: false,
                        borderColor: 'rgb(255, 0, 0)',
                        tension: 0.1,
                        borderWidth: 4
                    },
                ],
            },
            options: {
                responsive: true,
                scales: {
                    x: {
                        title: {
                            display: true,
                            text: 'Time',
                        },
                    },
                    y: {
                        title: {
                            display: true,
                            text: '°C',
                        },
                    },
                },
            },
        });

        return () => {
            chartInstance.destroy();
        };
    }, [data]);

    return (
        <div style={{ width: '500px', height: '300px', position: 'relative' }}>
            <canvas id="temp-chart" style={{ position: 'absolute', left: 50, top: 0, width: '100%', height: '100%' }}/>
        </div>
    );
};

export default TempChart;