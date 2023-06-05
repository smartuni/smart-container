export default function Checkbox({ label, id }) {
    return (
        <label className="inline-flex items-cetner mt-3">
            <input type="checkbox" className="h-5 w-5" value={id} />
            <span className="ml-2 text-gray-700">{label}</span>
        </label>
    )
}