import { useEffect, useState } from "react"
import { axiosInstance } from "@/utils/axiosInstance"
export const useContainers = () => {
  const [containers, setContainers] = useState([])

  useEffect(() => {
    (async () => {
      try {
        // fetch sensors and containers from backend then combine sensors per containers

        const sensorsRes = await axiosInstance.get('http://178.128.192.215:80/api/sensor/')
        const containersRes = fetch('http://178.128.192.215:80/api/container/')

        const sensorsData = sensorsRes.data

        const containersData = containersRes.data.map(container => ({
          ...container,
          sensors: sensorsData.filter(sensor => sensor.owner === container.container_id)
        }))

        setContainers(containersData)
      } catch { }
    })()
  }, [])

  return containers
}
