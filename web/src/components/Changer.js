function Changer(props){
    return (
        <div style={{ display: "flex", flexDirection: "column"}}>
            <button onClick={props.onUp}>{props.up}</button>
            <button onClick={props.onDown}>{props.down}</button>
        </div>
    )
}

export default Changer;