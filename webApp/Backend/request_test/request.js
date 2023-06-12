async function fetchSensorList() {
  const response = await fetch("http://178.128.192.215/api/sensor_list");
  const data = await response.json();
  console.log(data);
}

async function fetchSensorDetail(id) {
  const response = await fetch(`http://127.0.0.1:8000/api/sensor_detail/`, {
    method: "GET",
    body: JSON.stringify({ id: id }),
  });
  const data = await response.json();
  console.log(data);
}

async function fetchContainerLocation() {
  const containerResponse = await fetch(
    "http://127.0.0.1:8000/api/container_list"
  );
  const containerData = await containerResponse.json();
  console.log(
    "Doing fetch for container location",
    containerData[0].container_id
  );

  const response = await fetch(
    "http://127.0.0.1:8000/api/container_location/",
    {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ id: containerData[0].container_id }),
    }
  );
  const data = await response.json();
  console.log(data);
}
async function fetchUserData() {
  const userResponse = await fetch("http://127.0.0.1:8000/api/user_list");
  const containerData = await userResponse.json();

  console.log(containerData);
}


const onSubmit = async () => {
  const res = fetch("http://178.128.192.215:80/api/signIn/", {
    method: "POST",
    headers: {
     // "Content-Type": "application/json",
    },
    mode: "cors",
    body: JSON.stringify({
      username: "admin",
      password: "admin",
    }),
    credentials: "include",
  }).then((response) => {
    console.log("Test");
    console.log(response.body)
    return response.json();
  }).then((data) => {
    console.log(data);

  }).catch((error) => {
    console.log(error);
  });

  // const response_body = await res.json(); // Parse the response body as JSON
  // console.log(response_body)

  // if (res.ok) {
  //   const user = extract_user(response_body); // Call the extract_user function with the response body

  //   window.location.href = "/dashboard";

  //   return user;
  // } else {
  //   return null;
  // }
};

// const extract_user = (response) => {
//   let access_jwt_str = response?.access;

//   let jwt_payload_base64 = access_jwt_str?.split(".")[1];

//   let jwt_payload = Buffer.from(jwt_payload_base64, "base64"); //equivalent to atob

//   let user = JSON.parse(jwt_payload);

//   return user;
// };


async  function testConnection(){
  const res = await fetch("http://178.128.192.215:80/api/test_connection") 
  const response_body = await res.json(); // Parse the response body as JSON
  console.log(response_body)
}
onSubmit()