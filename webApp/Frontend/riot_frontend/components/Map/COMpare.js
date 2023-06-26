import { useEffect, useState } from "react";
import axiosInstance from "axios";
import Map from "@/components/Map/Map";
import styles from "../../styles/mapPopup.module.css";

const DEFAULT_CENTER = [53.5511, 9.9937];

export const ContainersMap = () => {
  const [containers, setContainers] = useState([]);

  useEffect(() => {
    const fetchContainers = async () => {
      try {
        const containerResponse = await axiosInstance.get(
          "http://178.128.192.215:8000/api/container/"
        );

        const containersWithSensorData = await Promise.all(
          containerResponse.data.map(async (container) => {
            const sensorResponse = await axiosInstance.get(
              `http://178.128.192.215:8000/api/sensor/${container.container_id}`
            );

            const sensorData = sensorResponse.data;

            return {
              ...container,
              sensor_data: sensorData,
            };
          })
        );

        setContainers(containersWithSensorData);
      } catch (error) {
        console.error("Error fetching containers:", error);
      }
    };

    fetchContainers();
  }, []);

  return (
    <Map width="100%" height={400} center={DEFAULT_CENTER} zoom={12}>
      {({ TileLayer, Marker, Popup }) => (
        <>
          <TileLayer
            url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
            attribution='&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
          />
          {containers.map((container) => {
            const {
              container_id,
              location,
              container_content,
              container_door_closed,
              container_start,
              container_destination,
              container_time,
              sensor_data,
            } = container;

            const latitude = sensor_data?.latitude; // Assuming latitude is available in the sensor_data object
            const longitude = sensor_data?.longitude; // Assuming longitude is available in the sensor_data object

            const position = [latitude, longitude] || DEFAULT_CENTER;

            return (
              <Marker key={container_id} position={position} className="Marker">
                <Popup className={styles.popup}>
                  <p>Container ID: {container_id}</p>
                  <p>Container location: {location}</p>
                  <p>Container content: {container_content}</p>
                  <p>Container door closed: {container_door_closed}</p>
                  <p>Container start: {container_start}</p>
                  <p>Container destination: {container_destination}</p>
                  <p>Last opened: {container_time}</p>
                  {sensor_data && (
                    <>
                      <p>Sensor type: {sensor_data.sensor_type}</p>
                      <p>Sensor data: {sensor_data.sensor_data}</p>
                      <p>Sensor time: {sensor_data.sensor_time}</p>
                      <p>Latitude: {latitude}</p>
                      <p>Longitude: {longitude}</p>
                    </>
                  )}
                </Popup>
              </Marker>
            );
          })}
        </>
      )}
    </Map>
  );
};
