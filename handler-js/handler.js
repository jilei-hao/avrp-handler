import useGatewayHelpers from './gateway_helpers.js';

const numberOfWorkers = 2;

async function RunHandler() {
  console.log("[AVRP-Handler]: Starting handler...");
  console.log("[AVRP-Handler]: authenticating to gateway server...");
  const { 
    getHandlerTasks 
  } = await useGatewayHelpers("http://localhost:6060", "avrpdev", "avrp@dev");

  console.log("[AVRP-Handler]: Starting timer...");

  const onTimerTick = async () => {
    console.log("[AVRP-Handler]: Timer tick");
    console.log("-- checking handler tasks...");
    const handlerTasks = await getHandlerTasks();
    console.log("-- handler tasks: ", handlerTasks);
  }

  setInterval(onTimerTick, 5000);
}

export {
  RunHandler,
}