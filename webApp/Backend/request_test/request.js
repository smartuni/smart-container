function testCSRFToken(){

//const csrftoken = getCookie('csrftoken');

fetch('http://178.128.192.215:80/api//', {
  method: 'POST',
  headers: {
    'Content-Type': 'application/json',
    //'X-CSRFToken': csrftoken
  },
  body: JSON.stringify({
    // request body
  })
})
.then(response => {
  // handle response
})
.catch(error => {
  // handle error
});
}

function getCookie(name) {
  let cookieValue = null;
  if (document.cookie && document.cookie !== '') {
      const cookies = document.cookie.split(';');
      for (let i = 0; i < cookies.length; i++) {
          const cookie = cookies[i].trim();
          // Does this cookie string begin with the name we want?
          if (cookie.substring(0, name.length + 1) === (name + '=')) {
              cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
              break;
          }
      }
  }
  return cookieValue;
}


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
    "http://178.128.192.215:80/api/container_list"
  );
  //const csrftoken = getCookie('csrftoken');

  const containerData = await containerResponse.json();
  console.log(containerData);
  const response = await fetch(
    "http://178.128.192.215:80/api/container_location/",
    {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
//        "X-CSRFToken": csrftoken
      },
      body: JSON.stringify({id: containerData[0].container_id}),
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

async function fetchTestConnection(){
  const response = await fetch(
    "http://178.128.192.215:8000/api/test_connection/");
    const data = await response.json();
    console.log(data);
}

fetchContainerLocation();
