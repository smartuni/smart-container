import { useEffect, useState, useRef } from "react";
import axios from "axios";
import { axiosInstance } from "@/utils/axiosInstance";

export const useContainers = async () => {
  const [containers, setContainers] = useState([]);

  const list = useRef([]);


  const onSubmit = async () => {

    console.log("Containers are fetched!");
    const res = await fetch("http://178.128.192.215:8000/api/container/", {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        "Authorization": "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoiYWNjZXNzIiwiZXhwIjoxNjg3NTQyNjMwLCJpYXQiOjE2ODc1NDIzMzAsImp0aSI6IjcxYTUyMGJlYjk3YTQ1YmM5OGE5NzZkOTYyMTFhZDY4IiwidXNlcl9pZCI6ImQwNjk5MTM1LTAyNzEtNDY3ZS1iMDUyLTc2YzQ3ZWIzOWI5NSIsInVzZXJuYW1lIjoiZW1pbHlsdWNpYS5hbnRvc2NoQGhhd2hhbWJ1cmcuZGUiLCJmaXJzdE5hbWUiOiJFbWlseSIsImxhc3RuYW1lIjoiQW50b3NjaCJ9.ja8RIUcysQvqyQSuNOEvJ6JLRZo8KekMKOBKaEQhsVM"
      },

    });
    var data = await res.json() // Parse the response body as JSON


    console.log("Container List: " + data);
    return data;

    if (res.ok) {
      const newList = extract_containers(response_body); // Call the extract_user function with the response body 
      localStorage.setItem('containerlist', JSON.stringify(newList));
      console.log(localStorage);
      console.log(newList);
      window.location.href = "/dashboard";
      return newList;
    } else {
      console.log("Response not OK!");
      return null;
    }
  };

  // const extract_containers = (response) => {
  //   let access_jwt_str = response?.access;
  //   let jwt_payload_base64 = access_jwt_str?.split('.')[1]; // TODO: Should it be [1]?
  //   let jwt_payload = Buffer.from(jwt_payload_base64, 'base64'); //equivalent to atob
  //   let list = JSON.parse(jwt_payload);
  //   return list;
  // };

  onSubmit()
};
