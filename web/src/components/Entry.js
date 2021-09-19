import Changer from "./Changer";

function Entry(props){
    const incriment = (amount) => {
        return () => {
            const  newValue = props.value+amount;
            props.onChange(newValue);
        }
    }

    return(
        <div style={{ display: "flex", height: "300px"}}>
            <div style={{ alignSelf: "center", textAlign: "center", width: "500px", fontSize:"75px", margin: "20px"}}>
                {props.format(props.value)}
            </div>

            <div style={{ display: "flex", margin: "20px"}}>
                {
                    props.values.map(value => <Changer up={`+${value}`} down={`-${value}`} onUp={incriment(value)} onDown={incriment(-value)} />)
                }
            </div>
        </div>
    )
}

export default Entry;