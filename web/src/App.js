import { useState } from 'react';
import './App.css';
import Action from './views/Action';
import Setup from './views/Setup';

function App() {
  const [setup, setSetup] = useState(true);
  const [targetTime, setTargetTime] = useState(0);
  const [targetDistance, setTargetDistance] = useState(0);

  const onStart = ({distance, time}) => {
    setTargetTime(time);
    setTargetDistance(distance);
    setSetup(false);
  }

  return (
    <div style={{display: "flex", justifyContent: "center"}}>
      { setup ? <Setup onStart={onStart}/> : <Action targetTime={targetTime} targetDistance={targetDistance}/> }
    </div>
  );
}


export default App;
