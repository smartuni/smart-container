import React, { useState, useEffect } from 'react';
import { Bar } from 'react-chartjs-2';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend,
} from 'chart.js';

ChartJS.register(
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend
);

const BarChart = ({data}) => {
  const [chartData, setChartData] = useState({
    datasets: [],
  });

  const [chartOptions, setChartOptions] = useState({});

  useEffect(() => {
    setChartData({
        labels: data.map((d) => d.time),
        datasets: [
            {
                label: 'Temperature in °C',
                data: data.map((d) => d.temperature),
                borderColor: 'rgb(53, 162, 235)',
                backgroundColor: 'rgb(53, 162, 235, 0.4',
              }, 
        ]
    })
    setChartOptions({
        scales: {
            y: {
              beginAtZero: true,
              title: {
                display: true,
                text: '°C',
                color: 'white',
              },
              grid: {
                color: 'rgba(0, 0, 0, 0.1)',
              },
              ticks: {
                color: 'white',
              },
            },
            x: {
              grid: {
                display: false,
              },
              ticks: {
                color: 'white',
              },
            },
        },
        plugins: {
            legend: {
                position: 'top',
                labels: {
                    color: 'white',
                }
            },
            title: {
                display: true,
                text: 'Tempreture Bar chart',
                color: 'white',
            }
        },
        elements: {
            bar: {
              backgroundColor: 'blue', // Change the color of the bars
              borderWidth: 2, // Adjust the thickness of the bar borders
            },
        },
        maintainAspectRatio: false,
        responsive: true
    })
  }, [])

  return (
    <>
      <div className='w-full md:col-span-2 relative lg:h-[70vh] h-[50vh] m-auto p-4 border rounded-lg bg-white'>
        <Bar data={chartData} options={chartOptions} />
      </div>
    </>
  );
};

export default BarChart;
