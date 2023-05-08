import TempChart from "./temperature";

const tempData = [
    { time: '12:00', temperature: 23 },
    { time: '12:30', temperature: 24 },
    { time: '13:00', temperature: 26 },
    { time: '13:30', temperature: 25 },
    { time: '14:00', temperature: 23 },
  ];

const TemperatureChart = () => {
  return (
    <div>
      <div>
        <nav >
          <ul>
            <li><a href="/map/page">Home</a></li>
            <li><a href="#">About Us</a></li>
            <li><a href="#">Contact</a></li>
            <li><a href="#">Log out</a></li>
          </ul>
        </nav>
      </div>
      <h2>Temperature over the last 24 hours</h2>
      <TempChart data={tempData} />
    </div>
  );
};

export default TemperatureChart;