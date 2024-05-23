export default async function useGatewayHelpers(url, username, password) {
  let token = '';

  await fetch(`${url}/login`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({
      username: username,
      password: password
    })
  }).then((res) => {
    if (!res.ok) {
      throw new Error('Error authenticating to the gateway server!');
    }
    return res.json();
  }).then((data) => {
    token = data.token;
  })

  const getHandlerTasks = async () => {
    console.log("[useGatewayHelpers::getHandlerTasks] ");
    return fetch(`${url}/handler-tasks`, {
      method: 'GET',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': `Bearer ${token}`,
      },
    }).then((res) => {
      if (!res.ok) {
        throw new Error('Error fetching handler tasks!');
      }
    }).then((data) => {
      return data;
    });
  };

  const postModuleData = async (moduleDataHeader, ) => {
    
  };

  return {
    getHandlerTasks,
  };
}