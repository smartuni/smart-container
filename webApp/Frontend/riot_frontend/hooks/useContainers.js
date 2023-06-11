import { useEffect, useState } from "react"

export const useContainers = () => {
    const [containers, setContainers] = useState([])

    useEffect( () => {
      (async () => {
        try {
        // fetch sensors and containers from backend then combine sensors per containers
        
          const sensorsRes = await axiosInstance.get('/api/sensor_list/')
          const containersRes = await axiosInstance.get('/api/container_list')
  
          const sensorsData = sensorsRes.data
  
          const containersData = containersRes.data.map(container => ({
            ...container,
            sensors: sensorsData.filter(sensor => sensor.owner === container.container_id)
          }))
  
          setContainers(containersData)
        } catch {}
      })()
    }, [])

  return containers
}
