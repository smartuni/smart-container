import { ContainersMap } from "@/components/Map/ContainersMap"
import RecentOrders from "@/components/RecentOrders";

const MapPage = () => {
    return (
        <div style={{ width: 'calc(100vw - 90px)' , height: '100vh', display: 'grid' }}>
            {/* <div >Hi</div> */}
            <ContainersMap />
        </div>
    )
}

export default MapPage
