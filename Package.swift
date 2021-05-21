// swift-tools-version:5.3
import PackageDescription
let package = Package(
    name: "BluePad50v2",
    platforms: [
        .iOS(.v12)
    ],
    products: [
        .library(
            name: "BluePad50v2",
            targets: ["BluePad50v2"])
    ],
    targets: [
        .binaryTarget(
            name: "BluePad50v2",
            path: "BluePad50v2.framework")
    ])
