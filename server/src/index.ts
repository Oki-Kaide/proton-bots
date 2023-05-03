import cluster from 'cluster'
import { NUM_CPUS } from './constants'
import { main } from './process'

if (cluster.isMaster) {
  masterProcess();
} else {
  childProcess();  
}

function masterProcess() {
  console.log(`Master ${process.pid} is running`);

  for (let i = 0; i < NUM_CPUS; i++) {
    console.log(`Forking process number ${i}...`);
    cluster.fork();
  }

//   process.exit();
}

function childProcess() {
  console.log(`Worker ${process.pid} started`);
  main();

//   process.exit();
}