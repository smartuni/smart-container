import { useEffect, useState } from "react"
import axios from "axios";
// 178.128.192.215:5342
export const useContainers = async () => {
  const [containers, setContainers] = useState([])


  const res = await fetch('http://178.128.192.215:80/api/container/')
  const data = await res.json();

  return {
    props: { containers_data: data },
  };
}
//   useEffect(() => {
//     (async () => {
//       try {
//         // fetch sensors and containers from backend then combine sensors per containers

//         const sensorsRes = await axiosInstance.get('http://178.128.192.215:80/api/sensor_list/')
//         const containersRes = await axiosInstance.get('http://178.128.192.215:80/api/container_list/')

//         const sensorsData = sensorsRes.data

//         const containersData = containersRes.data.map(container => ({
//           ...container,
//           sensors: sensorsData.filter(sensor => sensor.owner === container.container_id)
//         }))

//         setContainers(containersData)
//       } catch { }
//     })()
//   }, [])

//   return containers
// }
