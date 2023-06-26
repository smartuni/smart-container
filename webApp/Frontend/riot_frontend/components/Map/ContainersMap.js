import { useEffect, useState } from "react";
import axiosInstance from "axios";
import Map from "@/components/Map/Map";
import styles from "../../styles/mapPopup.module.css";

const DEFAULT_CENTER = [54.17792343350527, 15.576558965969518];

export const ContainersMap = () => {
  const [containers, setContainers] = useState([]);

  console.log("Map of Containers!");

  useEffect(() => {
    const fetchContainers = async () => {
      try {
        const res2 = await fetch(
          "http://178.128.192.215:8000/api/signIn/refresh/",
          {
            method: "POST",
            headers: {
              "Content-Type": "application/json",
            },
            body: JSON.stringify({
              refresh:
                "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoicmVmcmVzaCIsImV4cCI6MTY4Nzc5ODgyNiwiaWF0IjoxNjg3NzEyNDI2LCJqdGkiOiI3ODliNDEyNmVhNmQ0MDFmYWQ3NjFlNWY1ZjZmNTA0MyIsInVzZXJfaWQiOiJkMDY5OTEzNS0wMjcxLTQ2N2UtYjA1Mi03NmM0N2ViMzliOTUiLCJ1c2VybmFtZSI6ImVtaWx5bHVjaWEuYW50b3NjaEBoYXdoYW1idXJnLmRlIiwiZmlyc3ROYW1lIjoiRW1pbHkiLCJsYXN0bmFtZSI6IkFudG9zY2gifQ.37wWnzKr02lm8RgSm01lgwq6bhaRR4rV8EPDRcvdcIA",
            }),
          }
        )
          .then((res) => {
            return res.json();
          })
          .then((response) => {
            const containerResponse = fetch(
              "http://178.128.192.215:8000/api/container/",
              {
                method: "GET",
                headers: {
                  "Content-Type": "application/json",
                  Authorization: "Bearer " + response["access"],
                },
              }
            );
            if (containerResponse) {
              console.log(
                "Containers are fetched! " + containerResponse + " Printed!"
              );
            }
            return containerResponse;
          });

        var data = await res2.json();
        console.log("containerResponse", data[0]);

        const res_array = [];
        for (let i in data) {
          res_array.push([data[i]]);
        }

        console.log("Container List: ", data);
        console.log("Container 1: ", data[0].container_id);

        setContainers(data);

        // The code below is a bit redundant, but gets the location, not yet as an array
        const locationTest = await fetch(
          "http://178.128.192.215:8000/api/signIn/refresh/",
          {
            method: "POST",
            headers: {
              "Content-Type": "application/json",
            },
            body: JSON.stringify({
              refresh:
                "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoicmVmcmVzaCIsImV4cCI6MTY4Nzc5ODgyNiwiaWF0IjoxNjg3NzEyNDI2LCJqdGkiOiI3ODliNDEyNmVhNmQ0MDFmYWQ3NjFlNWY1ZjZmNTA0MyIsInVzZXJfaWQiOiJkMDY5OTEzNS0wMjcxLTQ2N2UtYjA1Mi03NmM0N2ViMzliOTUiLCJ1c2VybmFtZSI6ImVtaWx5bHVjaWEuYW50b3NjaEBoYXdoYW1idXJnLmRlIiwiZmlyc3ROYW1lIjoiRW1pbHkiLCJsYXN0bmFtZSI6IkFudG9zY2gifQ.37wWnzKr02lm8RgSm01lgwq6bhaRR4rV8EPDRcvdcIA",
            }),
          }
        )
          .then((res) => {
            return res.json();
          })
          .then((response) => {
            const sensorResponse = fetch(
              "http://178.128.192.215:8000/api/container_location/",
              {
                method: "POST",
                headers: {
                  "Content-Type": "application/json",
                  Authorization: "Bearer " + response["access"],
                },
                body: JSON.stringify({
                  id: "3426b1dc-3b11-4685-b8ae-723dfa593c25",
                }),
              }
            );
            if (sensorResponse) {
              console.log("Container loc are fetched!" + sensorResponse);
            }
            return sensorResponse;
          });

        var locData = await locationTest.json();
        localStorage.setItem("locData", await locationTest.json());
        console.log("location data: ", localStorage);
        console.log("location data: ", locData);
      } catch (error) {
        console.error("Error fetching containers:", error);
      }
    };

    fetchContainers();
  }, []);

  console.log("List of Containers: ", containers);

  var localgps = localStorage.getItem("locData");
  var gps = [localgps.split(",")[0], localgps.split(",")[1]];
  console.log("gps data: ", gps);

  return (
    <Map width="100%" height={400} center={DEFAULT_CENTER} zoom={12}>
      {({ TileLayer, Marker, Popup }) => (
        <>
          <TileLayer
            url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
            attribution='&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
          />
          {
            <Marker position={gps} className="Marker"></Marker>
            /* {containers.map((container, container_id) => (
            <Marker
              key={container_id}
              position={gps}
              className="Marker"
            ></Marker>
          ))} */
          }
        </>
      )}
    </Map>
  );
};
