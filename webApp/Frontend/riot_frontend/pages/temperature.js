import React, { useEffect, useRef } from 'react';
import Chart from 'chart.js/auto';

const TempChart = ({ data }) => {
    const chartContainerRef = useRef(null);
    const chartInstanceRef = useRef(null);

    useEffect(() => {
        const chartCanvas = document.getElementById('temp-chart');
        const chartContainer = chartContainerRef.current;

        if (!chartCanvas || !chartContainer) {
            return;
        }

        chartInstanceRef.current = new Chart(chartCanvas, {
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
                plugins: {
                    legend: {
                        labels: {
                            filter: (l) => l.text !== 'Temperature in °C',
                        },
                    },
                },
            },
        });

        return () => {
            chartInstanceRef.current?.destroy();
        };
    }, [data]);

    return (
        <div
            style={{
                width: '100%',
                aspectRatio: '16/9',
                position: 'relative',
            }}
            ref={chartContainerRef}
        >
            <canvas
                id="temp-chart"
                style={{
                    position: 'absolute',
                    top: 0,
                    left: 0,
                    width: '100%',
                    height: '100%',
    
      }}
    />
        </div>
    );
};

export default TempChart;
