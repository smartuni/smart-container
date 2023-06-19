import { useEffect, useState } from "react"

import Router from "next/router"
import axios from "axios";
// 178.128.192.215:5342
export const useContainers = async () => {
  const [containers, setContainers] = useState([])
  var containers_data = []
  function sendProps() {
    Router.push({
      pathname: "/dashboard",
      query: {
        containers_data,
      }
    });
  }


  useEffect(() => {
    (async () => {
      try {
        // fetch sensors and containers from backend then combine sensors per containers

        const sensorsRes = await axiosInstance.get('http://178.128.192.215:80/api/sensor/')
        const containersRes = await axiosInstance.get('http://178.128.192.215:80/api/container/')

        const sensorsData = sensorsRes.data

        const containersData = containersRes.data.map(container => ({
          ...container,
          sensors: sensorsData.filter(sensor => sensor.owner === container.container_id)
        }))

        setContainers(containersData)
        containers_data = containers
      } catch { }
    })()
  }, [])

  // return containers
  sendProps()
}


