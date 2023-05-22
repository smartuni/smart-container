
export const container = [
    {
      Container: {
        id: "ConUUID",
        start: "start",
        dest: "dest",
        doorStatus: "doorStatus",
        content: "content",
        userId: "userId",
        crashed: "crashed?",
        threshold: {
          string: {
            min: "min",
            max: "max",
          }
        }
    },

    Container: {
      id: "ConUUID",
      start: "start",
      dest: "dest",
      doorStatus: "doorStatus",
      content: "content",
      userId: "userId",
      crashed: "crashed?",
      threshold: {
        string: {
          min: "min",
          max: "max",
        }
      }
  },

    User: {
      id: "UserUUID",
      firstName: "firstName",
      lastName: "lastName",
      email: "email",
      password: "password",
      company: "company",
      role: "role",
    },

    SensorData: {
      id: "SensUUID",
      dataType: "dataType",
      value: "value",
      datetime: "datetime",
      containerId: "containerId",
    }


  }
      
]



 