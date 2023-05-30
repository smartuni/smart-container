async function fetchSensorList() {
  const response = await fetch("http://127.0.0.1:8000/api/sensor_list");
  return response;
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
  const userResponse = await fetch(
    "http://127.0.0.1:8000/api/user_list"
  );
  const containerData = await userResponse.json();

  console.log(containerData);
}

fetchUserData();
