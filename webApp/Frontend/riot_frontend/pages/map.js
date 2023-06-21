import { ContainersMap } from "@/components/Map/ContainersMap"
import RecentOrders from "@/components/RecentOrders";
import { useContainers } from "@/hooks/useContainers";

const MapPage = () => {
    const containers = useContainers()

    return (
        <div style={{ width: 'calc(100vw - 90px)' , height: '100vh', display: 'grid' }}>
            {/* <div >Hi</div> */}
            <ContainersMap containers={containers} />
        </div>
    )
}

export default MapPage
