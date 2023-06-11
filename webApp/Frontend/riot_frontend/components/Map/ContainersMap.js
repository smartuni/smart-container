import Map from "@/components/Map/Map";
import styles from '../../styles/mapPopup.module.css'

const DEFAULT_CENTER = [53.5511, 9.9937];
// const markers = [
//   { name: 'Container 1', location: [53.55587, 10.02439], temp: 32, humidity: 50, acceleration: 30, doorStatus:'Opened', lastOpened: '23/02/23' },
//   { name: 'Container 2', location: [53.55513463677272, 9.992930792175889], temp: 34, humidity: 30, acceleration: 30, doorStatus:'Closed', lastOpened: '23/02/23'  },
//   { name: 'Container 3', location: [53.53952514227034, 10.0049117958243], temp: 55,  humidity: 20, acceleration: 30  , doorStatus:'Closed', lastOpened: '23/02/23' },
// ];


export const ContainersMap = ({ containers }) => {
    return (
        <Map width="100%" height="400" center={DEFAULT_CENTER} zoom={12}>
            {({ TileLayer, Marker, Popup }) => (
                <>
                    <TileLayer
                        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
                        attribution="&copy; <a href=&quot;http://osm.org/copyright&quot;>OpenStreetMap</a> contributors"
                    />
                    {containers.map((container, index) => (
                        // render containers data as markers
                        <Marker key={index} position={marker.location} className="Maker">
                            <Popup className={styles.popup}>
                                <p> {container.container_id}</p>

                                {container.sensors.map(sensor => (
                                    <p key={sensor.sensor_type}>{sensor.sensor_type}: {sensor.sensor_data}</p>
                                ))}

                                <p>LastOpened: {sensor.sensor_time}</p>
                            </Popup>
                        </Marker>
                    ))}

                </>
            )}
        </Map>
    )
}

